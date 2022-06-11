#include "../tools/LogIdentifier.hpp"
#include "Room.hpp"

Room::Room(std::string creator, int selected_mode/*, room_stirage *general storage*/) {
    type = ROOM_TYPE_CHANNEL;
    mode = selected_mode;
//    name = room_storage->get_serial_name();
    room_users->add_nickname(creator);
    std::cout   << LogIdentifier::info
                << "user "
                << creator
                << " create a new room"
                << std::endl;
}

Room::Room(std::string creator, std::string joiner) {
    type = ROOM_TYPE_CHAT;
    mode = ROOM_MODE_PRIVATE;
    room_name = creator + " & " + joiner + "'s chat";
    room_users->add_nickname(creator);
    room_users->add_nickname(joiner);
    std::cout   << LogIdentifier::info
                << "users "
                << creator
                << " and "
                << joiner
                << " join to private chat"
                << std::endl;
}

Room::Room(std::string creator, int selected_mode, std::string set_room_name) {
    type = ROOM_TYPE_CHANNEL;
    mode = selected_mode;
    room_name = set_room_name;
    room_users->add_nickname(creator);
    std::cout   << LogIdentifier::info
                << "user "
                << creator
                << " create a new room with name: "
                << set_room_name;
                << std::endl;
}

std::string Room::get_room_name() {return (room_name);}

void Room::set_room_name(std::string new_name) {
    std::cout   << LogIdentifier::info()
                << "room "
                << room_name
                << " swap name to "
                << new_name
                << std::endl;
    room_name = new_name;
}