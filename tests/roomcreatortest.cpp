#include "../tools/LogIdentifier.hpp"
#include "../srv_inside/RoomCreator.hpp"
#include "../srv_inside/RoomStorage.hpp"

int main(){
    RoomStorage *tmpRoomStorage = new RoomStorage();
    RoomCreator *tmpCreator = new RoomCreator("Gibson", tmpRoomStorage);


}