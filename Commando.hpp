#ifndef IRC_COMMANDO_HPP
#define IRC_COMMANDO_HPP

#define NICKNAME_IS_WRONG   113
#define NICKNAME_IS_GIVEN   114
#define NICKNAME_HAS_VALID  115
#define NEW_USER_CREATE     116

#include "srv_inside/CommandLine.hpp"
#include "Serv.hpp"

//https://github.com/levensta/IRC-Server
//Realisation List:
//PASS          -
//NICK (1Arg)   -
//NICK (2Arg)   - OK
//USER          - OK
//OPER          -
//QUIT          -
//PRIVMSG       -
//AWAY(on/off)  - OK
//NOTICE        -
//WHO           -
//WHOIS         -
//WHOWAS        -
//MODE          -
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

    //-----------------------------validators-----------------------------
    int     nickname_validator(std::string nickname);                       //ok
};


#endif //IRC_COMMANDO_HPP