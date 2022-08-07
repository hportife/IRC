#ifndef IRC_SERV_HPP
#define IRC_SERV_HPP

#define FLG_SRV_WORK 2000
#define FLG_SRV_DOWN 2010

#include <queue>
#include <iostream>
#include <sys/poll.h>

#include "srv_inside/Room.hpp"
#include "srv_inside/RoomCreator.hpp"
#include "srv_inside/RoomStorage.hpp"
#include "srv_inside/User.hpp"
#include "srv_inside/UserStorage.hpp"
#include "srv_inside/NicknameStorage.hpp"
#include "srv_inside/CommandLine.hpp"

class Serv {
private:
    RoomStorage                 *general_room_storage;
    UserStorage                 *general_user_storage;
    NicknameStorage             *general_nickname_storage;
    std::queue<CommandLine *>   tasks;
    std::vector<pollfd>	        general_polls;
    int                         worked_flag;

public:
    Serv();//ok
    ~Serv();
    RoomStorage                 *getRoomStorage()const;//ok
    UserStorage                 *getUserStorage()const;//ok
    NicknameStorage             *getNicknameStorage()const;//ok
    std::queue<CommandLine *>   *GetTasks()const;//ok
    std::vector<pollfd>	        *GetPolls()const;//ok
    void                        shutDown();//ok
};


#endif //IRC_SLAVE_SERV_HPP
