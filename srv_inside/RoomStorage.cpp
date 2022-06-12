#include "../tools/LogIdentifier.hpp"
#include "RoomStorage.hpp"

RoomStorage::RoomStorage() {
    std::cout   << LogIdentifier::info()
                << "Room storage has been created"
                << std::endl;
}
RoomStorage::~RoomStorage() {
    std::cout   << LogIdentifier::info()
                << "Room storage has been deleted"
                << std::endl;
}

RoomStorage::