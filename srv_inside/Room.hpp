#ifndef IRC_ROOM_HPP
#define IRC_ROOM_HPP

#define ROOM_TYPE_CHAT      0
#define ROOM_TYPE_CHANNEL   1
#define ROOM_MODE_PRIVATE   301
#define ROOM_MODE_PUBLIC    302
#define USER_IS_OPER        311
#define USER_IS_NOT_OPER    312

#include "User.hpp"
#include "NicknameStorage.hpp"
#include <vector>
#include <algorithm>

class Room {
private:
    std::string     room_name;
    NicknameStorage *room_users;
    int             type;
    int             mode;

public:
    Room(std::string creator, std::string joiner);
    Room(std::string creator, int selected_mode);
    Room(std::string creator, int selected_mode, std::string set_room_name);
    ~Room();

    std::string get_room_name();
    void        set_room_name(std::string new_name);
    int         user_join(std::string joined_user);
    int         user_leave(std::string leaved_user);
    int         select_mode(int selected_mode);
    int         is_oper(std::string nickname);
};


#endif //IRC_ROOM_HPP
