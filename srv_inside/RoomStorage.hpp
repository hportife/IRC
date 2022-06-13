#ifndef IRC_ROOMSTORAGE_HPP
#define IRC_ROOMSTORAGE_HPP

#define ROOM_IN_STORAGE             400
#define ROOM_NOT_IN_STORAGE         401
#define DELETE_HAS_BEEN_COMPLETE    402

#include "Room.hpp"

class RoomStorage
{
private:
    std::vector<Room>   room_storage;
    int                 serial_counter;

public:
    RoomStorage();
    ~RoomStorage();

    void        add_room(Room room_for_add);
    int         search_conflicts(Room *inspected_room);
    int         get_room_position_in_storage(Room *room);
    int         delete_room_from_storage(Room *room);
    void        display_room_storage();
    std::string get_serial_name(Room *for_this_room);
};
#endif