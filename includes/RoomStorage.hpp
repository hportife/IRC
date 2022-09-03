#ifndef IRC_ROOMSTORAGE_HPP
#define IRC_ROOMSTORAGE_HPP

#include "Room.hpp"
#include "defines.hpp"

class RoomStorage
{
private:
    std::vector<Room *>   room_storage;
    int                 serial_counter;

    std::vector<Room *>::iterator get_position_iterator(Room const *room);
    int get_room_position_in_storage(Room const *room) const;

public:
    RoomStorage();

    ~RoomStorage();

    void        add_room(Room *room_for_add);
    int         search_conflicts(Room const *inspected_room);
    int         search_conflicts_with_name(std::string const inspected_room_name);
    int         delete_room_from_storage(Room const *room);
    void        delete_user_from_rooms(std::string nickname, std::string message);
    void        display_room_storage() const;
    Room        *getRoom(std::string room_name) const;
    //get_room_storage - нужен ли этот мето и что он должен возвращать,
    //всё хранилище как вектор или чисто список названий комнат
    // и нужно ли выводить приватные комнаты?
};
#endif