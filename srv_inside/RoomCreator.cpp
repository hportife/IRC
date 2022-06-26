#include "../tools/LogIdentifier.hpp"
#include "RoomCreator.hpp"

RoomCreator::RoomCreator(Room *room_for_tmp_creator, RoomStorage *general_storage) {
    this->general_storage = general_storage;
    tmp_room = room_for_tmp_creator;
    std::cout   << LogIdentifier::info()
                << "tmp room creator has been created"
                << std::endl;
}

RoomCreator::RoomCreator(std::string creator_nickname, RoomStorage *general_storage) {
    this->general_storage = general_storage;
    this->creator_nickname = creator_nickname;
    std::cout   << LogIdentifier::info()
                << creator_nickname
                << " start create a room"
                << std::endl;
}

RoomCreator::RoomCreator(std::string creator_nickname, RoomStorage *general_storage,
                         std::string name_for_room) {
    this->general_storage = general_storage;
    this->creator_nickname = creator_nickname;
    tmp_room_name = name_for_room;
    std::cout   << LogIdentifier::info()
                << creator_nickname
                << " start create a room with name "
                << name_for_room
                << std::endl;
}