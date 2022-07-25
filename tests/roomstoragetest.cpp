#include "../tools/LogIdentifier.hpp"
#include "../srv_inside/Room.hpp"
#include "../srv_inside/RoomStorage.hpp"

//c++ -std=c++98 roomstoragetest.cpp ../tools/LogIdentifier.cpp ../srv_inside/Room.cpp ../srv_inside/User.cpp ../srv_inside/RoomStorage.cpp ../srv_inside/NicknameStorage.cpp

int main(void){
	Room *room1, *room2, *room3, *room4;
	//так как комнаты будут создаваться с помощью
	//криейтора, то он должен будет следить за корректностью
	//передаваемых в конструктор параметров, поэтому условно
	// параметры здесь уже завалидированы криейтором.
	room1 = new Room("salaman", ROOM_MODE_PRIVATE, "salamander_room");//OK
	room2 = new Room("vik", ROOM_MODE_PRIVATE, "vikRoom");//OK
	room3 = new Room("yyyyyy", ROOM_MODE_PUBLIC, "1111122221231146134623462546235123462346134625734746");//OK
	room4 = new Room("121212", ROOM_MODE_PUBLIC, "ola");//OK

	//Создание тестовой комнаты
	std::cout << LogIdentifier::info("--------------") << "Creating an array of rooms\n";
	RoomStorage *testRoomStorage = new RoomStorage();
	testRoomStorage->add_room(room1);
	testRoomStorage->add_room(room2);
	testRoomStorage->add_room(room3);
	testRoomStorage->add_room(room4);
	std::cout << LogIdentifier::info("--------------") << "Output of an array of rooms\n";
	testRoomStorage->display_room_storage();
	std::cout << LogIdentifier::info("--------------") << "Delete room4 from an array of rooms\n";
	testRoomStorage->delete_room_from_storage(room4);
	std::cout << LogIdentifier::info("--------------") << "Search conflicts from an array of rooms\n";
	testRoomStorage->search_conflicts(room3);
}