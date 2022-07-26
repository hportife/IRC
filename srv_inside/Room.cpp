#include "../tools/LogIdentifier.hpp"
#include "Room.hpp"

Room::Room(std::string creator, std::string set_room_name) {
    //так как комнаты будут создаваться с помощью
    //криейтора, то он должен будет следить за корректностью
    //передаваемых в конструктор параметров.
//    set_mode(selected_mode);
    this->room_name = set_room_name;
    this->room_users = new NicknameStorage();
    this->room_users->add_nickname(creator);
    this->set_oper(creator);
    this->room_params = initRoomParams();
    std::cout   << LogIdentifier::info("FROM_ROOM_" + this->room_name)
                << "user " << creator << " create a new room with name: "
                << set_room_name << std::endl;
}

std::map<std::string, bool> Room::initRoomParams(){
    std::map<std::string, bool> tmp_room_params;
    tmp_room_params.insert(std::pair<std::string, bool>("p", false));
    tmp_room_params.insert(std::pair<std::string, bool>("s", false));
    tmp_room_params.insert(std::pair<std::string, bool>("t", false));
    tmp_room_params.insert(std::pair<std::string, bool>("n", false));
    tmp_room_params.insert(std::pair<std::string, bool>("m", false));
    tmp_room_params.insert(std::pair<std::string, bool>("l", false));
    tmp_room_params.insert(std::pair<std::string, bool>("k", false));
    return (tmp_room_params);
}
//_____________________GETTERS__________________________________________
std::string Room::get_room_name() const {return (this->room_name);}

int         Room::get_users_capacity() const {return (this->room_users
                                                        ->get_capacity());}

std::string Room::get_room_password() const { return (this->room_password);}

bool        Room::get_param_value(std::string param_name){
    return (this->room_params[param_name])
}

//_____________________SETTERS__________________________________________
void Room::set_room_name(std::string const new_name) {
    std::cout   << LogIdentifier::info("FROM_ROOM_" + this->room_name)
                << "room " << this->room_name << " swap name to "
                << new_name << std::endl;
    this->room_name = new_name;
}

void Room::set_room_password(std::string const password){
    this->room_params["k"] = true;
    this->room_password = password;
}

void Room::set_room_parameter(std::string const parameter){
    this->room_params[parameter] = true;
}

void Room::unset_room_parameter(std::string const parameter){
    this->room_params[parameter] = false;
}

void Room::set_oper(std::string const new_oper) {
    room_users->set_value(new_oper) = USER_IS_OPER;
}

void Room::unset_oper(std::string const deleted_oper){
    room_users->set_value(deleted_oper) = USER_IS_NOT_OPER;
}

//____________________METHODS___________________________________________

void Room::add_user(std::string const nickname){
    std::cout   << LogIdentifier::info("ROOMCLASS_" + this->room_name)
                << "user " << nickname << " added to room"<< std::endl;
    this->room_users->add_nickname(nickname);
}

void Room::delete_user(std::string const nickname){
    std::cout   << LogIdentifier::info("ROOMCLASS_" + this->room_name)
                << "user " << nickname << " deleted from room"<< std::endl;
    this->room_users->delete_nickname(nickname);
}

void Room::add_to_invite_list(std::string const nickname){
    this->invite_list.push_back(nickname);
}
//___________________CHECKERS______________________________________________
bool Room::is_oper(std::string nickname){
    if (this->room_users->get_value(nickname)
                                                == USER_IS_OPER)
        return (true);
    return (false);
}

bool Room::is_in_invite_list(std::string nickname){
    if (std::find(this->invite_list.begin(),
                  this->invite_list.end(), nickname)
                  != this->invite_list.end())
        return (true);
    return (false);
}