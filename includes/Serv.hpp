#ifndef IRC_SERV_HPP
#define IRC_SERV_HPP

#include <queue>
#include <iostream>
#include <sys/poll.h>

#include "Room.hpp"
#include "RoomCreator.hpp"
#include "RoomStorage.hpp"
#include "User.hpp"
#include "UserStorage.hpp"
#include "NicknameStorage.hpp"
#include "CommandLine.hpp"
#include "defines.hpp"
#include "Commando.hpp"
#include "Connect.hpp"

class Commando;

class Serv {
private:
    RoomStorage                 *general_room_storage;
    UserStorage                 *general_user_storage;
    NicknameStorage             *general_nickname_storage;
    std::queue<CommandLine *>   tasks;
    std::vector<pollfd>	        general_polls;
	Connect						*connect;
    int                         worked_flag;
    std::vector<std::string>    irc_oper_nicknames;
    Commando                    *general_comando;
    std::string                 password;
	unsigned short				port;

public:
    Serv(std::string password, unsigned short port);//ok
    ~Serv();
    RoomStorage                 *getRoomStorage()const;//ok
    UserStorage                 *getUserStorage()const;//ok
    NicknameStorage             *getNicknameStorage()const;//ok
    std::queue<CommandLine *>   *getTasks();//ok
    std::vector<pollfd>	        *getPolls();//ok
    std::vector<std::string>    *getOpers();//
    Commando                    *getCommando()const;//ok
    std::string                 getPassword()const;//ok
    void                        setPassword(std::string password);//
    void                        shutDown();//ok
    Connect                     *getConnect()const;
};


#endif //IRC_SLAVE_SERV_HPP
