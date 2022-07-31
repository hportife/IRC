#ifndef IRC_SERV_HPP
#define IRC_SERV_HPP

#include <queue>
#include <iostream>

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

public:
    Serv();
    ~Serv();
};


#endif //IRC_SLAVE_SERV_HPP
