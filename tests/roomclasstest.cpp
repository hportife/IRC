#include "../tools/LogIdentifier.hpp"
#include "../srv_inside/Room.hpp"

int main(void){
    Room *room1, *room2, *room3, *room4;
    room1 = new Room("salamander", ROOM_MODE_PRIVATE, "salamander_room");
    room2 = new Room("vik", ROOM_MODE_PRIVATE, "vikRoom");
    room3 = new Room("yyyyyy", ROOM_MODE_PUBLIC, "1111122221231146134623462546235123462346134625734746");
    room4 = new Room("121212", ROOM_MODE_PUBLIC, "ola");

    room1->get_room_name();
    room2->get_room_name();
    room3->get_room_name();
    room4->get_room_name();
}