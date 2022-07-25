#include "../tools/LogIdentifier.hpp"
#include "Room.hpp"

Room::Room(std::string creator, int selected_mode,
           std::string set_room_name) {
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
std::string Room::get_room_password() const { this->room_password;}

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
int Room::user_join(std::string const joined_user) {
    if (this->room_users->search_a_conflict(joined_user)
        == ERR_NICKNAMEINUSE){
        std::cout   << LogIdentifier::error("FROM_ROOM_" + this->room_name)
                    << "user " << joined_user
                    << " is already in the channel "
                    << this->room_name << std::endl;
        return (USER_IN_ROOM);
    }
    this->room_users->add_nickname(joined_user);
    std::cout   << LogIdentifier::debug("FROM_ROOM_" + this->room_name)
                << "user " << joined_user
                << " join in the channel "
                << this->room_name << std::endl;
    return (JOIN_COMPLETE);
}

int Room::user_leave(std::string const leaved_user) {
    if (this->room_users->search_a_conflict(leaved_user)
        != ERR_NICKNAMEINUSE){
        std::cout   << LogIdentifier::error("FROM_ROOM_" + this->room_name)
                    << "user " << leaved_user
                    << " not in the channel "
                    << this->room_name << std::endl;
        return (USER_NOT_IN_ROOM);
    }
    this->room_users->delete_nickname(leaved_user);
    std::cout   << LogIdentifier::debug("FROM_ROOM_" + this->room_name)
                << "user " << leaved_user
                << " leave the channel "
                << this->room_name << std::endl;
    return (LEAVE_COMPLETE);
}

int Room::is_oper(std::string nickname) {
    if (this->oper_nicknames->search_a_conflict(nickname)
        == ERR_NICKNAMEINUSE)
        return (USER_IS_OPER);
    return (USER_IS_NOT_OPER);
}

int Room::delete_user(std::string const reporter,
                        std::string const deleted_user){
    if (is_oper(reporter) == USER_IS_OPER){
        std::cout   << LogIdentifier::debug("FROM_ROOM_" + this->room_name)
                    << reporter << " kick "
                    << deleted_user << " from "
                    << this->room_name << std::endl;
        if (is_oper(deleted_user) == USER_IS_OPER)
            this->oper_nicknames->delete_nickname(deleted_user);
        return (user_leave(deleted_user));
    }
    std::cout   << LogIdentifier::error("FROM_ROOM_" + this->room_name)
                << "user " << reporter << " not oper in room "
                << this->room_name << " for delete users"
                << std::endl;
    return (USER_IS_NOT_OPER);
}