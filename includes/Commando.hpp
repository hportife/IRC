#ifndef IRC_COMMANDO_HPP
#define IRC_COMMANDO_HPP

#include "Serv.hpp"
#include "CommandLine.hpp"
#include "defines.hpp"
#include "Parser.hpp"

class Serv;

class Commando {
private:
    Serv        *general_serv;
    Commando();

    std::string servToIrcErr(int eventId);//преобразовывает идентификатор эвента
    //из серверного в ИРКовый

public:
    Commando(Serv *server_class);
    ~Commando();

    int     NickCmd(std::string old_nickname, std::string new_nickname);//OK - NICK (2Arg)
    int     NickCmd(int id, std::string new_nickname);                   //ok - NICK (1Arg)
    void    AwayCmd(std::string user_nickname, std::string message);     //ok - AWAY(on)
    void    UserConnect(int id);                                            //ok
    int     UserCmd(int id, std::string clientname,
                        std::string realname);                              //ok - USER
    int     OperCmd(std::string nickname, std::string password);          //ok - OPER
    void    ModeLCmd(std::string room_name, int limit);                 //ok - MODE l
    void    ModeOCmd(std::string room_name, std::string nickname,
                              bool rights); //нужно дописать                                //Nok - MODE 0
    void    setUserParam(std::string nickname, std::string param,
                         bool value);                                       //ok - MODE user
    void    setRoomParam(std::string room_name, std::string param,
                         bool value);                                       //nok - MODE room
    void    QuitCmd(int id, std::string message);
    void    PrivmsgToUser(int id, std::string message);
    void    PrivmsgToChannel(std::string channel_name,
                             std::string message);
    void    JoinCmd(int id, std::string channel_name);
    void    InviteCmd(int id, std::string channel_name);
    void    KickCmd(int kicker_id, int kickem_id);


    void    WrongReqMessage(const std::string& user_nickname, int eventId,
                            const std::string& command);

    void    AnswerMessage(const std::string& user_nickname, int eventId,
                          const std::string& command);

    //-----------------------------validators-----------------------------
    int     nickname_validator(std::string nickname);                       //ok
};


//https://github.com/levensta/IRC-Server
//Realisation List:
//PASS          -
//NICK (1Arg)   -
//NICK (2Arg)   - OK
//USER          - OK
//OPER          - OK
//QUIT          -
//PRIVMSG       -
//AWAY(on/off)  - OK
//NOTICE        -
//WHO           -
//WHOIS         -
//WHOWAS        -
//MODE          -
//  room
//      i       - OK//если лимит 0 - то ограничения нет
//      o       -
//  user        - OK
//TOPIC         -
//JOIN          -
//INVITE        -
//KICK          -
//PART          -
//NAMES         -
//LIST          -
//RESTART       -
//KILL          -
//REHASH???
//WALLOPS       -
//PING / PONG   -
//ISON          -
//USERHOST      -
//VERSION       -
//INFO          -
//ADMIN         -
//TIME          -
/*  ("p", false));
    ("s", false));
    ("t", false));
    ("n", false));
    ("m", false));
    ("k", false));*/

#endif //IRC_COMMANDO_HPP
