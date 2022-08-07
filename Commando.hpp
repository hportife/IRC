#ifndef IRC_COMMANDO_HPP
#define IRC_COMMANDO_HPP

#define NICKNAME_IS_WRONG   113
#define NICKNAME_IS_GIVEN    114

#include "srv_inside/CommandLine.hpp"
#include "Serv.hpp"

//https://github.com/levensta/IRC-Server
//Realisation List:
//PASS          -
//NICK (1Arg)   -
//NICK (2Arg)   - OK
//USER          -
//OPER          -
//QUIT          -
//PRIVMSG       -
//AWAY          - OK
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

    void    getNextCommandLine();//OK
    int     executeActualCommand();//NOK
    int     swapNickname(std::string old_nickname, std::string new_nickname);//OK
    int     setAwayMsg(std::string user_nickname);//Ok
    int     setAwayMsg(std::string user_nickname, std::string message);//ok
};


#endif //IRC_COMMANDO_HPP
