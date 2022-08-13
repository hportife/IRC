#include "tools/LogIdentifier.hpp"
#include "Serv.hpp"

Serv::Serv(std::string password) {
    this->password = password;
    this->general_room_storage = new RoomStorage();
    this->general_nickname_storage = new NicknameStorage();
    this->general_user_storage = new UserStorage(
            general_nickname_storage);
    this->worked_flag = FLG_SRV_WORK;
    this->general_comando = new Commando(&this);
    std::cout << LogIdentifier::info("SERVERCLASS_")
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
Commando *Serv::getCommando() const {
    return (this->general_comando);
}
std::string Serv::getPassword() const {
    return (this->password);
}
void Serv::setPassword(std::string password) {
    this->password = password;
}
void Serv::shutDown(){
    this->worked_flag = FLG_SRV_DOWN;
}
std::vector <std::string> *Serv::getOpers() {
    return (&this->irc_oper_nicknames);
}