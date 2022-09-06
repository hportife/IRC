#include "includes/LogIdentifier.hpp"
#include "includes/Commando.hpp"

//!!!!!!!!
#include "srcs_connect/Connect.hpp"
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
    if (nickname_validator(new_nickname) != NICKNAME_HAS_VALID)
    {
        this->WrongReqMessage(new_nickname, ERR_ERRONEUSNICKNAME, "");
        return (NICKNAME_IS_WRONG);
    }
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
    //СООБЩЕНИЕ ВЫДАЧЕ НОВОГО НИКА
    this->AnswerMessage(new_nickname, NICKNAME_IS_GIVEN, "NICK");
    return (NICKNAME_IS_GIVEN);
}

int Commando::NickCmd(int id, std::string new_nickname) {
    int rpl = nickname_validator(new_nickname);
    if (rpl != NICKNAME_HAS_VALID) {
        WrongReqMessage(new_nickname, rpl, "NICK");
        return (rpl);
    }
    this->general_serv
            ->getNicknameStorage()
            ->add_nickname(new_nickname);
    this->general_serv
            ->getUserStorage()
            ->search_by_id(id)
            ->set_nickname(new_nickname);
    if (!this->general_serv
            ->getUserStorage()
            ->search_by_id(id)->get_user_realname().empty()) {
        this->general_serv
                ->getUserStorage()
                ->search_by_id(id)
                ->setReadyness();
        //ОТПРАВИТЬ MOTD
    }
    AnswerMessage(new_nickname, NICKNAME_IS_GIVEN, "NICK");
    return (NICKNAME_IS_GIVEN);
}

void Commando::AwayCmd(std::string user_nickname, std::string message) {
    this->general_serv->getUserStorage()
                        ->search_by_nickname(user_nickname)
                        ->setAwayMsg(message);
    //сообщение: эвэй установлен
    AnswerMessage(user_nickname, RPL_AWAY, message);
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
    if (!idToNick(id).empty())
        this->general_serv
                ->getUserStorage()
                ->search_by_id(id)
                ->setReadyness();
    return (NEW_USER_CREATE);
}

int Commando::OperCmd(std::string nickname, std::string password) {
    if (!password.empty() && this->general_serv
        ->getPassword().compare(password) != 0) {
        WrongReqMessage(nickname, ERR_PASSWDMISMATCH, password);
        return (WRONGPASSWORD);
    }
    this->general_serv->getOpers()->push_back(nickname);
    return (USER_IS_OPER);
}

void Commando::ModeLCmd(std::string room_name, int limit) {
    Channel(room_name)
        ->set_user_limit(limit);
}

void Commando::ModeOCmd(std::string room_name, std::string oper_nick,
                        std::string nickname, bool rights) {
    if (Channel(room_name) != NULL) {
        if (!Channel(room_name)->is_oper(oper_nick)) {
            //отправить сообщение что oper_nick
            //не имеет права давать права оперов
            WrongReqMessage(oper_nick, ERR_NOPRIVILEGES, "mode");
            return;
        }
        if (this->general_serv
                ->getNicknameStorage()
                ->search_a_conflict(nickname) != ERR_NICKNAMEINUSE) {
            //сообщение что не верно введён никнейм
            WrongReqMessage(nickname, ERR_ERRONEUSNICKNAME, "");
            return;
        }
        if (!Channel(room_name)
                ->isInRoom(nickname)){
            //сообщение что пользователя в комнате нет
            WrongReqMessage(nickname, ERR_USERNOTINCHANNEL, room_name);
            return;
        }
        if (rights) {
            Channel(room_name)->set_oper(nickname);
            //отправить сообщение о выданных правах
            AnswerMessage(nickname, RPL_YOUREOPER, "");
        } else {
            Channel(room_name)->unset_oper(nickname);
            //отправить сообщение о снятых правах
            AnswerMessage(nickname, RPL_BREAKOPER, "");
        }
    }
    else //ОТПРАВИТЬ СООБЩЕНИЕ ОБ ОТСУТСТВИИ КОМНАТЫ
        WrongReqMessage(room_name, ERR_NOSUCHCHANNEL, "");
}

void Commando::setUserParam(std::string nickname, std::string param,
                            bool value) {
    this->general_serv
        ->getUserStorage()
        ->search_by_nickname(nickname)
        ->setUserParamValue(param, value);
    //сообщение что парамерты установлены
}

void Commando::setRoomParam(std::string room_name, std::string param,
                            bool value) {
    Channel(room_name)->setRoomParameter(param, value);
    //сообщение что параметры установлены
}

//-----------------------------validators-----------------------------------

int Commando::nickname_validator(std::string nickname) {
    if (nickname.length() > 9 || nickname.empty()) {
        //сообщение: корявый ник
        WrongReqMessage(nickname, ERR_ERRONEUSNICKNAME, "");
        return (NICKNAME_IS_WRONG);
    }
    if (this->general_serv
                ->getNicknameStorage()
                ->search_a_conflict(nickname)
        == ERR_NICKNAMEINUSE) {
        //сообщение: ник занят
        WrongReqMessage(nickname, ERR_NICKNAMEINUSE, "");
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
        case ERR_NOSUCHCHANNEL:
            msg += " :No such channel\n";
            break;
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
        case ERR_ERRONEUSNICKNAME:
            msg += " :Erroneus nickname\n";
            break;
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

void    Commando::AnswerMessage(const std::string& user_nickname, int eventId, const std::string& command) {
    std::string	msg = ":Amateur42_IRC ";
    std::stringstream	ss;

    ss << eventId;
    msg += ss.str() + " " + user_nickname;
    switch (eventId)
    {
        case RPL_BREAKOPER:
            msg += " :You are not an IRC operator anymore\n";
            break;
        case RPL_INVITING:
            msg += command + "\n";
            break;
        //"<channel> <mode> <mode params>"
        // channel user gets oper
        case RPL_CHANNELMODEIS:
            msg += "\n";
            break;
        case RPL_AWAY:
            msg += " " + command + "\n";
            break;
        case RPL_NOWAWAY:
            msg += " :You have been marked as being away\n";
            break;
        case RPL_WHOISOPERATOR:
            msg += " :is an IRC operator\n";
            break;
        case RPL_ENDOFWHOWAS:
            msg += " :End of WHOWAS\n";
            break;
        case RPL_LISTSTART:
            msg += "Channel :Users  Name\n";
            break;
        case RPL_NOTOPIC:
            msg += " :No topic is set\n";
            break;
        case RPL_SUMMONING:
            msg += " :Summoning user to IRC\n";
            break;
//        case RPL_ENDOFWHO:
//            msg += " " + command.getArgument(0) + " :End of /WHO list\n";
//            break;
        case RPL_ENDOFNAMES:
            msg += " :End of /NAMES list\n";
            break;
        case RPL_ENDOFLINKS:
            msg += " :End of /LINKS list\n";
            break;
        case RPL_ENDOFBANLIST:
            msg += " :End of channel ban list\n";
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
            msg += " :You are now an IRC operator\n";
            break;
        case RPL_REHASHING:
            msg += " :Rehashing\n";
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
            msg += " :End of /STATS report\n";
            break;
        case RPL_STATSUPTIME:
            msg += " :Server Up %d days %d:%02d:%02d\n";
            break;
        case RPL_UMODEIS:
            msg += "\n";
            break;
        case RPL_LUSEROP:
            msg += " :operator(s) online\n";
            break;
        case RPL_LUSERUNKNOWN:
            msg += " :unknown connection(s)\n";
            break;
        case RPL_LUSERCHANNELS:
            msg += " :channels formed\n";
            break;
        case RPL_LUSERME:
            msg += " :I have clients and servers\n";
            break;
        case RPL_ADMINME:
            msg += " :Administrative info\n";
            break;
        case NICKNAME_IS_GIVEN:
            msg += " :nickname is given:\n";
            break;
        default:
            msg += "UNKNOWN REPLY\n";
            break;
    }
//    logger.logUserMessage(msg, user, OUT);
    send(this->general_serv->getUserStorage()->search_by_nickname(user_nickname)->get_user_id(),
         msg.c_str(), msg.size(), 0);
}

Room *Commando::Channel(std::string room_name) {
    return (this->general_serv
            ->getRoomStorage()
            ->getRoom(room_name));
}

void Commando::PrivmsgToUser(int sender_id, int destination_id,
                             std::string message) {
    NoticeCmd(destination_id, message);
    if (this->general_serv
            ->getUserStorage()
            ->search_by_id(destination_id)
            ->isAwayMsg())
        NoticeCmd(sender_id, this->general_serv
                                ->getUserStorage()
                                ->search_by_id(destination_id)
                                ->getAwayMsg());
}

bool Commando::isCannelInServ(std::string room_name) {
    return (Channel(room_name) != NULL);
}

bool Commando::isNicknameInServ(std::string nickname) {
    return (this->general_serv
                ->getNicknameStorage()
            ->search_a_conflict(nickname) == ERR_NICKNAMEINUSE);
}

void Commando::NoticeCmd(int id, std::string message) {
    //отправить сообщение
}

void Commando::PrivmsgToChannel(std::string channel_name, std::string message) {
    if (!isCannelInServ(channel_name)) {
        //отправить сообщение о некорректном названии комнаты
        WrongReqMessage(channel_name, ERR_NOSUCHCHANNEL, "");
    }
    //иначе отправить сообщение в комнату
    //AnswerMessage(); ?
}

void Commando::InviteCmd(int id, std::string channel_name) {
    if (isCannelInServ(channel_name))
        Channel(channel_name)
            ->add_to_invite_list(idToNick(id));
    //сообщение: некорректное название комнаты
    WrongReqMessage(channel_name, ERR_NOSUCHCHANNEL, "");
}

void Commando::JoinCmd(int id, std::string channel_name) {
    if (isCannelInServ(channel_name))
    {
        if(Channel(channel_name)
                ->get_param_value("i")/*i==true*/ &&
                !Channel(channel_name)
                        ->is_in_invite_list(idToNick(id))/*invite==false*/){
            //сообщение о том что пользователь не может войти в инвайт-онли комнату
            WrongReqMessage(idToNick(id), ERR_INVITEONLYCHAN, channel_name);
        }
        Channel(channel_name)
                ->add_user(idToNick(id));
        //сообщение что пользователь вошёл в комнату
        AnswerMessage(channel_name, RPL_INVITING, idToNick(id));
        //Channel(channel_name) - убрать пользователя из инвайт листа ???
    } else {
        //сообщение о некорректном названии комнаты
        WrongReqMessage(channel_name, ERR_NOSUCHCHANNEL, "");
    }
}

std::string Commando::idToNick(int id) {
    return (this->general_serv
            ->getUserStorage()
            ->search_by_id(id)
            ->get_user_nickname());
}

void Commando::KickCmd(int kicker_id, int kickem_id, std::string channel_name) {
    if (isCannelInServ(channel_name)){
        if (Channel(channel_name)->is_oper(idToNick(kicker_id))){
            Channel(channel_name)->delete_user(idToNick(kickem_id));
            //сообщение в канал что пользователя кикнули
            //сообщение пользователю что его кикнули
        } else {
            //сообщение кикеру, что он не опер
            WrongReqMessage(idToNick(kicker_id), ERR_CHANOPRIVSNEEDED, channel_name);
        }
    }
    else {
        //сообщение о некорректном названии комнаты
        WrongReqMessage(channel_name, ERR_NOSUCHCHANNEL, "");
    }
}

void Commando::QuitCmd(int id, std::string message) {
    this->general_serv->getRoomStorage()->delete_user_from_rooms(idToNick(id), message);
    //в методе выше реализовать отправку сообщения о выходе пользователя
    this->general_serv->getNicknameStorage()->delete_nickname(idToNick(id));
    this->general_serv->getUserStorage()->delete_user_from_storage(this->general_serv
                                                                        ->getUserStorage()
                                                                        ->search_by_id(id));
    //УДАЛИТЬ ПОЛЬЗОВАТЕЛЯ ИЗ ПУЛА ФДШНИКОВ
    //ЗАКРЫТЬ СОЕДИНЕНИЕ
}