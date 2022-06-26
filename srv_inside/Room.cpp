#include "../tools/LogIdentifier.hpp"
#include "Room.hpp"

Room::Room(std::string creator, int selected_mode/*, room_storage *general storage*/) {
    this->mode = selected_mode;
//    name = room_storage->get_serial_name();
    room_users->add_nickname(creator);
    oper_nicknames->add_nickname(creator);
    std::cout   << LogIdentifier::info()
                << "user "
                << creator
                << " create a new room"
                << std::endl;
}

Room::Room(std::string creator/*, room_storage *general storage*/) {
    this->mode = ROOM_MODE_PRIVATE;
//    name = room_storage->get_serial_name();
    room_users->add_nickname(creator);
    oper_nicknames->add_nickname(creator);
    std::cout   << LogIdentifier::info()
                << "user "
                << creator
                << " create a new room"
                << std::endl;
}

Room::Room(std::string creator, int selected_mode, std::string set_room_name) {
//    type = ROOM_TYPE_CHANNEL;
    this->mode = selected_mode;
    room_name = set_room_name;
    room_users->add_nickname(creator);
    std::cout   << LogIdentifier::info()
                << "user "
                << creator
                << " create a new room with name: "
                << set_room_name;
                << std::endl;
}

std::string Room::get_room_name() const {return (this->room_name);}
int         Room::get_room_mode() const {return (this->mode);}

void Room::set_room_name(std::string const new_name) {
    std::cout   << LogIdentifier::info()
                << "room "
                << this->room_name
                << " swap name to "
                << new_name
                << std::endl;
    this->room_name = new_name;
}

int Room::user_join(std::string const joined_user) {
    if (room_users->search_a_conflict(joined_user) == ERR_NICKNAMEINUSE){
        std::cout   << LogIdentifier::error()
                    << "user "
                    << joined_user
                    << " is already in the channel "
                    << this->room_name
                    << std::endl;
        return (USER_IN_ROOM);
    }
    room_users->add_nickname(joined_user);
    std::cout   << LogIdentifier::debug()
                << "user "
                << joined_user
                << " join in the channel "
                << this->room_name
                << std::endl;
    return (JOIN_COMPLETE);
}

int Room::user_leave(std::string const leaved_user) {
    if (room_users->search_a_conflict(joined_user) != ERR_NICKNAMEINUSE){
        std::cout   << LogIdentifier::error()
                    << "user "
                    << joined_user
                    << " not in the channel "
                    << this->room_name
                    << std::endl;
        return (USER_NOT_IN_ROOM);
    }
    room_users->add_nickname(joined_user);
    std::cout   << LogIdentifier::debug()
                << "user "
                << joined_user
                << " leave the channel "
                << this->room_name
                << std::endl;
    return (LEAVE_COMPLETE);
}

int Room::set_mode(int const selected_mode) {
    this->mode = selected_mode;
    std::cout   << LogIdentifier::info()
                << "room "
                << this->room_name
                << " swap mode to "
                << selected_mode
                << std::endl;
}

int Room::is_oper(std::string nickname) {
    if (oper_nicknames->search_a_conflict(nickname) == ERR_NICKNAMEINUSE)
        return (USER_IS_OPER);
    return (USER_IS_NOT_OPER);
}

int Room::set_oper(std::string reporter, std::string new_oper) {
    if (oper_nicknames->search_a_conflict(reporter) == ERR_NICKNAMEINUSE &&
        oper_nicknames->search_a_conflict(new_oper) != ERR_NICKNAMEINUSE){
        oper_nicknames->add_nickname(new_oper);
        std::cout   << LogIdentifier::info()
                    << "oper "
                    << reporter
                    << " take a oper rights for user "
                    << new_oper
                    << std::endl;
        return (USER_IS_OPER);
    } else{
        std::cout   << LogIdentifier::error()
                    << "failed to assign operator"
                    << std::endl;
        return (USER_IS_NOT_OPER);
    }
}

int Room::get_users_capacity() {
    return (room_users->get_capacity());
}

int Room::unset_oper(std::string const reporter, std::string const deleted_oper){
    if (is_oper(reporter) == USER_IS_OPER
        && is_oper(deleted_oper) == USER_IS_OPER){
        this->oper_nicknames->delete_nickname(deleted_oper);
        std::cout   << LogIdentifier::debug()
                    << "oper "
                    << reporter
                    << "removed the oper rights from"
                    << deleted_oper
                    << std::endl;
        return (0);
    }
    else if (is_oper(deleted_oper) == USER_IS_NOT_OPER){
        std::cout   << LogIdentifier::error()
                    << deleted_oper
                    << " is not oper";
        return (USER_IS_NOT_OPER);
    } else if (is_oper(reporter) == USER_IS_NOT_OPER){
        std::cout   << LogIdentifier::error()
                    << reporter
                    << " is not oper";
        return (USER_IS_NOT_OPER);
    }
}