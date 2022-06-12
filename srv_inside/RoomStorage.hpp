#ifndef IRC_ROOMSTORAGE_HPP
#define IRC_ROOMSTORAGE_HPP

#include "Room.hpp"

class RoomStorage
{
private:
    std::vector<Room> room_storage;

public:
    RoomStorage();
    ~RoomStorage();

    void        add_room(Room room_for_add);
    Room        *search_by_nickname(std::string searched_nickname);
    Room        *search_by_id(int searched_id);
    int         get_room_position_in_storage(Room *room);
    int         delete_room_from_storage(Room *room);
    void        display_room_storage();
    std::string get_serial_name();
};
#endif