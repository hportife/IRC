#include "../includes/LogIdentifier.hpp"
#include "../includes/RoomCreator.hpp"
#include "../includes/RoomStorage.hpp"

int main(){
    RoomStorage *tmpRoomStorage = new RoomStorage();
    RoomCreator *tmpCreator = new RoomCreator("Gibson", tmpRoomStorage);


}