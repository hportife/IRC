#include "../tools/LogIdentifier.hpp"
#include "RoomCreator.hpp"
#include <cstddef>        // std::size_t

//RoomCreator::RoomCreator(Room *room_for_tmp_creator, RoomStorage *general_storage) {
//    this->general_storage = general_storage;
//    tmp_room = room_for_tmp_creator;
//    std::cout   << LogIdentifier::info()
//                << "tmp room creator has been created"
//                << std::endl;
//}

RoomCreator::RoomCreator(std::string creator_nickname, RoomStorage *general_storage) {
    this->general_storage = general_storage;
    this->creator_nickname = creator_nickname;
    this->tmp_room_name = general_storage->get_serial_name();
    this->tmp_room_mode = ROOM_MODE_PRIVATE;
    std::cout   << LogIdentifier::info()
                << creator_nickname
                << " start create a room"
                << std::endl;
}

RoomCreator::RoomCreator(std::string creator_nickname, RoomStorage *general_storage,
                         std::string name_for_room) {
    this->general_storage = general_storage;
    this->creator_nickname = creator_nickname;
    this->tmp_room_name = name_for_room;
    this->tmp_room_mode = ROOM_MODE_PRIVATE;
    std::cout   << LogIdentifier::info()
                << creator_nickname
                << " start create a room with name "
                << name_for_room
                << std::endl;
}

RoomCreator::RoomCreator(std::string creator_nickname, RoomStorage *general_storage,
                         std::string name_for_room, int mode_for_room) {
    this->general_storage = general_storage;
    this->creator_nickname = creator_nickname;
    this->tmp_room_name = name_for_room;
    this->tmp_room_mode = mode_for_room;
    std::cout   << LogIdentifier::info()
                << creator_nickname
                << " start create a room with name "
                << name_for_room
                << std::endl;
}

RoomCreator::~RoomCreator() {
    std::cout   << LogIdentifier::debug()
                << "Room creator for room "
                << this->tmp_room_name
                << " has destroyed"
                << std::endl;
}

int RoomCreator::room_name_validation() {
	if (this->tmp_room_name.length() > 200){
        std::cout   << LogIdentifier::error()
                    << "room_name_validation: ROOM_NAME_IS_TOO_LONG"
                    << std::endl;
        return (ROOM_NAME_IS_TOO_LONG);
    }
	char b = 7;
	int found_b = int(tmp_room_name.find_first_of(b, 1));
	int found = int(tmp_room_name.find_first_of(", #&", 1));
	else if (!((tmp_room_name[0] == '#' || tmp_room_name[0] == '&') && (found_b == -1 && found == -1))){
        std::cout   << LogIdentifier::error()
                    << "room_name_validation: ROOM_NAME_IS_WRONG"
                    << std::endl;
        return (ROOM_NAME_IS_WRONG);
    }
    return (ROOM_NAME_IS_OK);
}

int RoomCreator::get_finished_room() const{
    if (!this->creator_nickname.empty()
        && !this->tmp_room_name.empty()){
        this->tmp_room = new Room(this->creator_nickname,
                                  this->tmp_room_mode,
                                  this->tmp_room_name);
        this->general_storage->add_room(tmp_room);
        return (ROOM_IS_FINISHED);
    }
    return (ROOM_IS_NOT_GOT);
}