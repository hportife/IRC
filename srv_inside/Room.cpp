#include "../tools/LogIdentifier.hpp"
#include "Room.hpp"

Room::Room(std::string creator, int selected_mode,
           std::string set_room_name) {
    //так как комнаты будут создаваться с помощью
    //криейтора, то он должен будет следить за корректностью
    //передаваемых в конструктор параметров.
    set_mode(selected_mode);
    this->room_name = set_room_name;
    this->room_users = new NicknameStorage();
    this->oper_nicknames = new NicknameStorage();
    this->room_users->add_nickname(creator);
    this->oper_nicknames->add_nickname(creator);
    std::cout   << LogIdentifier::info("FROM_ROOM_" + this->room_name)
                << "user " << creator << " create a new room with name: "
                << set_room_name << std::endl;
}

std::string Room::get_room_name() const {return (this->room_name);}
int         Room::get_room_mode() const {return (this->mode);}
int         Room::get_users_capacity() { return (this->room_users->get_capacity());}

void Room::set_room_name(std::string const new_name) {
    std::cout   << LogIdentifier::info("FROM_ROOM_" + this->room_name)
                << "room " << this->room_name << " swap name to "
                << new_name << std::endl;
    this->room_name = new_name;
}

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

int Room::set_mode(int const selected_mode) {
    if (selected_mode == ROOM_MODE_PRIVATE ||
            selected_mode == ROOM_MODE_PUBLIC){
        this->mode = selected_mode;
        std::cout   << LogIdentifier::info("FROM_ROOM_" + this->room_name)
                    << "room " << this->room_name
                    << " swap mode to " << selected_mode
                    << std::endl;
        return (selected_mode);
    }
    std::cout   << LogIdentifier::error("FROM_ROOM_" + this->room_name)
                << selected_mode
                << " is not a room mode\n";
    return (-1);
}


int Room::is_oper(std::string nickname) {
    if (this->oper_nicknames->search_a_conflict(nickname)
        == ERR_NICKNAMEINUSE)
        return (USER_IS_OPER);
    return (USER_IS_NOT_OPER);
}

int Room::set_oper(std::string reporter, std::string new_oper) {
    if (this->oper_nicknames->search_a_conflict(reporter)
        == ERR_NICKNAMEINUSE &&
        this->oper_nicknames->search_a_conflict(new_oper)
        != ERR_NICKNAMEINUSE){
        this->oper_nicknames->add_nickname(new_oper);
        std::cout   << LogIdentifier::info("FROM_ROOM_" + this->room_name)
                    << "oper " << reporter
                    << " take a oper rights for user "
                    << new_oper << std::endl;
        return (USER_IS_OPER);
    }
    std::cout   << LogIdentifier::error("FROM_ROOM_" + this->room_name)
                << "failed to assign operator"
                << std::endl;
    return (USER_IS_NOT_OPER);
}

int Room::unset_oper(std::string const reporter,
                     std::string const deleted_oper){
    if (is_oper(reporter) == USER_IS_OPER
        && is_oper(deleted_oper) == USER_IS_OPER){
        this->oper_nicknames->delete_nickname(deleted_oper);
        std::cout   << LogIdentifier::debug("FROM_ROOM_" + this->room_name)
                    << "oper " << reporter
                    << " removed the oper rights from "
                    << deleted_oper << std::endl;
    }
    else if (is_oper(deleted_oper) == USER_IS_NOT_OPER){
        std::cout   << LogIdentifier::error("FROM_ROOM_" + this->room_name)
                    << deleted_oper << " is not oper" << std::endl;
        return (USER_IS_NOT_OPER);
    } else if (is_oper(reporter) == USER_IS_NOT_OPER){
        std::cout   << LogIdentifier::error("FROM_ROOM_" + this->room_name)
                    << reporter << " is not oper" << std::endl;
        return (USER_IS_NOT_OPER);
    }

    return (0);
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