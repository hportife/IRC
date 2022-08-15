#ifndef IRC_COMMANDO_HPP
#define IRC_COMMANDO_HPP

#define NICKNAME_IS_WRONG   113
#define NICKNAME_IS_GIVEN   114
#define NICKNAME_HAS_VALID  115
#define NEW_USER_CREATE     116
#define WRONGPASSWORD       117

#include "srv_inside/CommandLine.hpp"
#include "Serv.hpp"

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

class Commando {
private:
    CommandLine *commandLine;
    Serv        *general_serv;

public:
    Commando(Serv *server_class);
    ~Commando();

    void    getNextCommandLine();                                           //OK
    int     executeActualCommand();                                         //NOK
    int     swapNickname(std::string old_nickname, std::string new_nickname);//OK - NICK (2Arg)
    int     setAwayMsg(std::string user_nickname);                          //Ok - AWAY(off)
    int     setAwayMsg(std::string user_nickname, std::string message);     //ok - AWAY(on)
    int     userCommand(std::string nickname, int id,
                        std::string clientname,
                        std::string realname);                              //ok - USER
    int     operLogin(std::string nickname, std::string password);          //ok - OPER
    void    setRoomLimit(std::string room_name, int limit);                 //ok - MODE l
    void    setRoomOperRights(std::string room_name, std::string nickname,
                              bool rights);                                 //ok - MODE 0
    void    setUserParam(std::string nickname, std::string param,
                         bool value);                                       //ok - MODE user
    void    setRoomParam(std::string room_name, std::string param,
                         bool value);                                       //nok - MODE room

    //-----------------------------validators-----------------------------
    int     nickname_validator(std::string nickname);                       //ok
};

/*  ("p", false));
    ("s", false));
    ("t", false));
    ("n", false));
    ("m", false));
    ("k", false));*/

#endif //IRC_COMMANDO_HPP
