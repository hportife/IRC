#include "../tools/LogIdentifier.hpp"
#include "RoomStorage.hpp"

RoomStorage::RoomStorage() {
    std::cout   << LogIdentifier::info("FROM_ROOMSTORAGE_CLASS_")
                << "Room storage has been created"
                << std::endl;
    serial_counter = 1;
}
RoomStorage::~RoomStorage() {
    std::cout   << LogIdentifier::info("FROM_ROOMSTORAGE_CLASS_")
                << "Room storage has been deleted"
                << std::endl;
}

int RoomStorage::search_conflicts(Room const *inspected_room) {
    return (search_conflicts_with_name(inspected_room->get_room_name()));
}

int RoomStorage::search_conflicts_with_name(std::string const inspected_room_name){
    for (int i = 0; i < room_storage.size(); ++i) {
        if (room_storage[i]->get_room_name().compare(inspected_room_name) == 0){
            std::cout   << LogIdentifier::error("FROM_ROOMSTORAGE_CLASS_")
                        << "when searching for a conflict, the room "
                        << inspected_room_name
                        << " was found in the storage"
                        << std::endl;
            return (ROOM_IN_STORAGE);
        }
    }
    std::cout   << LogIdentifier::debug("FROM_ROOMSTORAGE_CLASS_")
                << "when searching for a conflict, the room "
                << inspected_room_name
                << " was not found in the storage"
                << std::endl;
    return (ROOM_NOT_IN_STORAGE);
}

void RoomStorage::add_room(Room *room_for_add) {
    if (search_conflicts(room_for_add) == ROOM_NOT_IN_STORAGE)
    {
        room_storage.push_back(room_for_add);
        std::cout   << LogIdentifier::info("FROM_ROOMSTORAGE_CLASS_")
                    << "the room "
                    << room_for_add->get_room_name()
                    << " entered storage"
                    << std::endl;
        return;
    }
    std::cout   << LogIdentifier::error("FROM_ROOMSTORAGE_CLASS_")
                << "the room "
                << room_for_add->get_room_name()
                << "was not added to the storage "
                   "because there is already a "
                   "room with the same name"
               <<  std::endl;
}

std::vector<Room *>::iterator RoomStorage::get_position_iterator(Room const *room){
    std::vector<Room *>::iterator ite = this->room_storage.end();
    std::vector<Room *>::iterator it = this->room_storage.begin();
    while (it != ite && (*it)->get_room_name() != room->get_room_name()) {
        it++;
    }
    return (it);
}

int RoomStorage::delete_room_from_storage(Room const *room) {
    if (search_conflicts(room) == ROOM_IN_STORAGE){
        std::cout << "YP!\n";
        room_storage.erase(get_position_iterator(room));
        std::cout   << LogIdentifier::debug("FROM_ROOMSTORAGE_CLASS_")
                    << "room has been delete from storage"
                    << std::endl;
        return (DELETE_HAS_BEEN_COMPLETE);
    } else if (search_conflicts(room) == ROOM_NOT_IN_STORAGE){
        std::cout   << LogIdentifier::error("FROM_ROOMSTORAGE_CLASS_")
                    << "searched room not in storage, abort delete"
                    << std::endl;
        return (ROOM_NOT_IN_STORAGE);
    } else{
        std::cout   << LogIdentifier::error("FROM_ROOMSTORAGE_CLASS_")
                   << "unexpected error in method delete_room_from_storage"
                   << std::endl;
        return (-1);
    }
}

void RoomStorage::display_room_storage() const{
    std::cout       << "room number\t| room name"
                    << std::endl;
    for (int i = 0; i < this->room_storage.size(); ++i) {
        std::cout   << i
                    << "\t\t| "
                    << this->room_storage[i]->get_room_name()
                    << std::endl;
    }
}

Room *RoomStorage::getRoom(std::string room_name) const {
    for (int i = 0; i < room_storage.size(); ++i) {
        if (room_storage[i]->get_room_name().compare(room_name) == 0){
            return (room_storage[i]);
        }
    }
    return (NULL);
}