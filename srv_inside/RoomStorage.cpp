#include "../tools/LogIdentifier.hpp"
#include "RoomStorage.hpp"

RoomStorage::RoomStorage() {
    std::cout   << LogIdentifier::info()
                << "Room storage has been created"
                << std::endl;
    serial_counter = 1;
}
RoomStorage::~RoomStorage() {
    std::cout   << LogIdentifier::info()
                << "Room storage has been deleted"
                << std::endl;
}

int RoomStorage::search_conflicts(Room *inspected_room) {
    for (int i = 0; i < room_storage.size(); ++i) {
        if (room_storage[i].get_room_name().compare(inspected_room) == 0){
            std::cout   << LogIdentifier::error()
                        << "when searching for a conflict, the room "
                        << inspected_room->get_room_name()
                        << " was found in the storage"
                        << std::endl;
            return (ROOM_IN_STORAGE);
        }
    }
    std::cout   << LogIdentifier::debug()
                << "when searching for a conflict, the room "
                << inspected_room->get_room_name()
                << " was not found in the storage"
                << std::endl;
    return (ROOM_NOT_IN_STORAGE);
}

void RoomStorage::add_room(Room room_for_add) {
    if (search_conflicts(&room_for_add) == ROOM_NOT_IN_STORAGE)
    {
        room_storage.push_back(room_for_add);
        std::cout   << LogIdentifier::info()
                    << "the room "
                    << room_for_add.get_room_name()
                    << " entered storage"
                    << std::endl;
        return;
    }
    std::cout   << LogIdentifier::error()
                << "the room "
                << room_for_add.get_room_name()
                << "was not added to the storage "
                   "because there is already a "
                   "room with the same name"
               <<  std::endl;
}

std::string RoomStorage::get_serial_name(Room *for_this_room) {
    if (for_this_room->get_room_type() == ROOM_TYPE_CHAT){
        std::cout   << LogIdentifier::debug()
                    << "serial name get for chat"
                    << std::endl;
        return ("#chat" + std::to_string(serial_counter++));
    } else if (for_this_room->get_room_type() == ROOM_TYPE_CHANNEL){
        std::cout   << LogIdentifier::debug()
                   << "serial name get for channel"
                   << std::endl;
        return ("#channel" + std::to_string(serial_counter++));
    }
}

int RoomStorage::get_room_position_in_storage(Room *room) {
    for (int i = 0; i < room_storage.size(); ++i) {
        if (room_storage[i] == room)
            return i;
    }
    return (-1);
}

int RoomStorage::delete_room_from_storage(Room *room) {
    if (search_conflicts(room) == ROOM_IN_STORAGE){
        room_storage.erase(get_room_position_in_storage(room));
        std::cout   << LogIdentifier::debug()
                    << "room has been delete from storage"
                    << std::endl;
        return (DELETE_HAS_BEEN_COMPLETE);
    } else if (search_conflicts(room) == ROOM_NOT_IN_STORAGE){
        std::cout   << LogIdentifier::error()
                    << "searched room not in storage, abort delete"
                    << std::endl;
        return (ROOM_NOT_IN_STORAGE);
    } else{
        std::cout   << LogIdentifier::error()
                   << "unexpected error in method delete_room_from_storage"
                   << std::endl;
        return (-1);
    }
}