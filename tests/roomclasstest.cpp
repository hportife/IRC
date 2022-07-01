#include "../tools/LogIdentifier.hpp"
#include "../srv_inside/Room.hpp"

int main(void){
    Room *room1, *room2, *room3, *room4;

    room1 = new Room("salamander", ROOM_MODE_PRIVATE, "salamander_room");//OK
    room2 = new Room("vik", ROOM_MODE_PRIVATE, "vikRoom");//OK
    room3 = new Room("yyyyyy", ROOM_MODE_PUBLIC, "1111122221231146134623462546235123462346134625734746");//OK
    room4 = new Room("121212", ROOM_MODE_PUBLIC, "ola");//OK

    room1->get_room_name();//OK
    room2->get_room_name();//OK
    room3->get_room_name();//OK
    room4->get_room_name();//OK

    room1->set_room_name(room2->get_room_name());//OK
    room2->set_room_name(room3->get_room_name());//OK
    room3->set_room_name(room4->get_room_name());//OK
    room4->set_room_name("paprika");//OK

    room1->get_room_mode();//OK
    room2->get_room_mode();//OK
    room3->get_room_mode();//OK
    room4->get_room_mode();//OK

    std::cout << LogIdentifier::error();
    room1->set_mode(112211);//ERROR
    room2->set_mode(ROOM_MODE_PUBLIC);//OK
    room3->set_mode(ROOM_MODE_PUBLIC);//OK
    std::cout << LogIdentifier::error();
    room4->set_mode(0);//ERROR

    room1->user_join("Roberto");//ok
    room2->user_join("Roberto");//ok
    room3->user_join("Roberto");//ok
    room4->user_join("Roberto");//ok
    room1->user_join("Rico");//ok
    room2->user_join("Rico");//ok
    room3->user_join("Rico");//ok
    room4->user_join("Rico");//ok
    room1->user_join("yyyyyy");//ok
    room2->user_join("yyyyyy");//ok
    room3->user_join("yyyyyy");//ok
    room4->user_join("yyyyyy");//ok

    std::cout << LogIdentifier::error();
    room1->user_join("Roberto");//error
    std::cout << LogIdentifier::error();
    room2->user_join("");//error

    room1->set_oper("salamander","Roberto");//ok
    room2->set_oper("vik", "Rico");//ok
    room3->set_oper("yyyyyy", "yyyyyy");//ok

    room1->unset_oper("Roberto", "salamander");//ok
    room2->unset_oper("Rico", "vik");//ok
    room3->unset_oper("yyyyyy", "yyyyyy");//ok
    room4->unset_oper("121212", "121212");//ok
}