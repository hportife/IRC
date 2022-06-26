#ifndef IRC_ROOMSTORAGE_HPP
#define IRC_ROOMSTORAGE_HPP

#define ROOM_IN_STORAGE             400
#define ROOM_NOT_IN_STORAGE         401
#define DELETE_HAS_BEEN_COMPLETE    402

#include "Room.hpp"

class RoomStorage
{
private:
    std::vector<Room *>   room_storage;
    int                 serial_counter;

public:
    RoomStorage();
    ~RoomStorage();

    int get_room_position_in_storage(Room const *room) const;
    std::string get_serial_name() const;

    void        add_room(Room const *room_for_add);
    int         search_conflicts(Room const *inspected_room);
    int         delete_room_from_storage(Room const *room);
    void        display_room_storage() const;
    //get_room_storage - нужен ли этот мето и что он должен возвращать,
    //всё хранилище как вектор или чисто список названий комнат
    // и нужно ли выводить приватные комнаты?
};
#endif