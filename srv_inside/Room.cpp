#include "Room.hpp"

Room::Room()
{
    std::cout << "DBG: create empty room\n";
}

Room::Room(int chat_creator_id, int chat_joiner_id)
{
    std::cout   << "DBG: create chat "
                << chat_creator_id << " & "
                << chat_joiner_id << " ID's\n";
    room_name = "chat";
    room_type = ROOM_TYPE_CHAT;
    //room_id = pool::get_room_id;
    room_user_qt = 2;
    room_users_id.push_back(chat_creator_id);
    room_users_id.push_back(chat_joiner_id);
}

Room::Room(std::string name, int creator_id)
{
    std::cout   << "DBG: create "
                << name << " channel\n";
    room_name = name;
    room_type = ROOM_TYPE_CHANNEL;
    //room_id = pool::get_room_id;
    room_user_qt = 1;
    room_users_id.push_back(creator_id);
    operator_id = creator_id;
}

int Room::get_room_type() {return (room_type);}

int Room::get_room_id() {return (room_id);}

int Room::get_users_qt() {return (room_user_qt);}

std::string Room::get_room_name() {return (room_name);}

void Room::join_to_room(int joiner_id)
{
    std::cout << "DBG: id " <<  joiner_id << " join to "
    room_user_qt++;
    room_users_id.push_back(joiner_id);
    std::sort(room_users_id.begin(), room_users_id.end());
}

void Room::out_of_room(int user_id)
{
    std::find(room_users_id.begin(), room_users_id.end(), user_id);//////////
}