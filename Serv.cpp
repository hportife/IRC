#include "tools/LogIdentifier.hpp"
#include "Serv.hpp"

Serv::Serv() {
    this->general_room_storage = new RoomStorage();
    this->general_nickname_storage = new NicknameStorage();
    this->general_user_storage = new UserStorage(
            general_nickname_storage);
    this->worked_flag = FLG_SRV_WORK;
    std::cout << LogIdentifier::info(SERVERCLASS_)
                << "Server class is start" << std::endl;
}
Serv::~Serv(){//need to add clear
     }
RoomStorage                 *Serv::getRoomStorage()const{
    return (this->general_room_storage);
}
UserStorage                 *Serv::getUserStorage()const{
    return (this->general_user_storage);
}
NicknameStorage             *Serv::getNicknameStorage()const{
    return
}
std::queue<CommandLine *>   *Serv::GetTasks()const{
    return (&this->tasks);
}
std::vector<pollfd>	        *Serv::GetPolls()const{
    return (&this->general_polls);
}
void Serv::shutDown(){
    this->worked_flag = FLG_SRV_DOWN;
}