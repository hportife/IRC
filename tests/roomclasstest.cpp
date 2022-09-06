#include "../includes/LogIdentifier.hpp"
#include "../includes/Room.hpp"

//c++ roomclasstest.cpp ../tools/LogIdentifier.cpp ../srv_inside/Room.cpp ../srv_inside/User.cpp ../srv_inside/NicknameStorage.cpp

int main(void){
    Room *room1, *room2, *room3, *room4;
    std::cout << "_____________STAGE_1_CALL_CONSTRUCTOR____________________________________\n";
    //так как комнаты будут создаваться с помощью
    //криейтора, то он должен будет следить за корректностью
    //передаваемых в конструктор параметров, поэтому условно
    // параметры здесь уже завалидированы криейтором.
    room1 = new Room("salaman", ROOM_MODE_PRIVATE, "salamander_room");//OK
    room2 = new Room("vik", ROOM_MODE_PRIVATE, "vikRoom");//OK
    room3 = new Room("yyyyyy", ROOM_MODE_PUBLIC, "1111122221231146134623462546235123462346134625734746");//OK
    room4 = new Room("121212", ROOM_MODE_PUBLIC, "ola");//OK
std::cout << "_____________STAGE_2_CALL_GET_ROOM_NAME____________________________________\n";
    std::cout << room1->get_room_name() << std::endl;//OK
    std::cout << room2->get_room_name() << std::endl;//OK
    std::cout << room3->get_room_name() << std::endl;//OK
    std::cout << room4->get_room_name() << std::endl;//OK

    std::cout << "_____________STAGE_3_CALL_SET_ROOM_NAME____________________________________\n";

    room1->set_room_name(room2->get_room_name());//OK
    room2->set_room_name(room3->get_room_name());//OK
    room3->set_room_name(room4->get_room_name());//OK
    room4->set_room_name("paprika");//OK
std::cout << "_____________STAGE_4_CALL_GET_ROOM_MODE____________________________________\n";
    std::cout << room1->get_room_mode() << std::endl;//OK
    std::cout << room2->get_room_mode() << std::endl;//OK
    std::cout << room3->get_room_mode() << std::endl;//OK
    std::cout << room4->get_room_mode() << std::endl;//OK
std::cout << "_____________STAGE_5_CALL_SET_MODE____________________________________\n";
    std::cout << LogIdentifier::error() << std::endl;
    room1->set_mode(112211);//ERROR
    room2->set_mode(ROOM_MODE_PUBLIC);//OK
    room3->set_mode(ROOM_MODE_PUBLIC);//OK
    std::cout << LogIdentifier::error() << std::endl;
    room4->set_mode(0);//ERROR
std::cout << "_____________STAGE_6_____________________________________\n";
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
    room3->user_join("yyyyyy");//err
    room4->user_join("yyyyyy");//ok
std::cout << "_____________STAGE_7_____________________________________\n";
    std::cout << LogIdentifier::error() << std::endl;
    room1->user_join("Roberto");//error
    std::cout << LogIdentifier::error() << std::endl;
    room2->user_join("");//error
std::cout << "_____________STAGE_8_____________________________________\n";
    room1->set_oper("salaman","Roberto");//ok
    room1->set_oper("salaman","Roberto");//ok
    room2->set_oper("vik", "Rico");//ok
    room3->set_oper("yyyyyy", "yyyyyy");//ok
std::cout << "_____________STAGE_9_____________________________________\n";
    room1->unset_oper("Roberto", "salamander");//ok
    room2->unset_oper("Rico", "vik");//ok
    room3->unset_oper("yyyyyy", "yyyyyy");//ok
    room4->unset_oper("121212", "121212");//ok
}