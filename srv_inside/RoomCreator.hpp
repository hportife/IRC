#ifndef IRC_ROOMCREATOR_HPP
#define IRC_ROOMCREATOR_HPP

#define ROOM_NAME_IS_OK         100
#define ROOM_NAME_IS_TOO_LONG   101
#define ROOM_NAME_IS_WRONG      102
#define ROOM_IS_NOT_GOT         103
#define ROOM_IS_FINISHED        104

#include "RoomStorage.hpp"
#include "Room.hpp"

class RoomCreator{
private:
    Room        *tmp_room;
    RoomStorage *general_storage;
    std::string creator_nickname;
    std::string tmp_room_name;
    int         tmp_room_mode;

public:
    RoomCreator(std::string creator_nickname,
                RoomStorage *general_storage);
    RoomCreator(std::string creator_nickname,
                RoomStorage *general_storage,
                std::string name_for_room);
    RoomCreator(std::string creator_nickname,
                RoomStorage *general_storage,
                std::string name_for_room,
                int mode_for_room);
    ~RoomCreator();


    int room_name_validation();
    int get_finished_room() const;
};

#endif