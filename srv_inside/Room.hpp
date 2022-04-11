#ifndef IRC_ROOM_HPP
#define IRC_ROOM_HPP

#define ROOM_TYPE_CHAT = 0
#define ROOM_TYPE_CHANNEL = 1

#include "user.hpp"
#include <vector>

class Room {
private:
    std::string             room_name;
    int                     room_type;
    int                     room_id;
    int                     room_user_qt;
    std::vector<int>        room_users_id;
    int                     operator_id;

public:
    Room();
    Room(int chat_creator_id, int chat_joiner_id);//для чатов. криейтор - создавший чат, джойнер - тот, с кем ео создали
    Room(std::string name, int creator_id);//для каналов. имя, айди из пула чатов, id создателя
    ~Room();

    int         get_room_type();
    int         get_room_id();
    int         get_users_qt();
    std::string get_room_name();

    void        join_to_room(int joiner_id);
    void        out_of_room(int user_id);
};


#endif //IRC_ROOM_HPP
