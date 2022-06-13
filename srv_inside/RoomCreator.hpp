#ifndef IRC_ROOMCREATOR_HPP
#define IRC_ROOMCREATOR_HPP

#include "RoomStorage.hpp"
#include "Room.hpp"

class RoomCreator{
private:
    Room        *tmp_room;
    RoomStorage *general_storage;
    std::string creator_nickname;
    std::string tmp_room_name;

public:
    RoomCreator(std::string creator_nickname, RoomStorage *general_storage);
    RoomCreator(std::string creator_nickname, RoomStorage *general_storage, std::string name_for_room);
    RoomCreator(Room *room_for_tmp_creator, RoomStorage *general_storage);
    ~RoomCreator();

    int room_name_validation();
};

#endif