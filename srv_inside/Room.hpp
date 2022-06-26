#ifndef IRC_ROOM_HPP
#define IRC_ROOM_HPP

//#define ROOM_TYPE_CHAT          0
//#define ROOM_TYPE_CHANNEL       1
#define ROOM_MODE_PRIVATE       301
#define ROOM_MODE_PUBLIC        302
#define USER_IS_OPER            311
#define USER_IS_NOT_OPER        312
#define USER_IN_ROOM            321
#define USER_NOT_IN_ROOM        322
#define JOIN_COMPLETE           323
#define LEAVE_COMPLETE          324

#include "User.hpp"
#include "NicknameStorage.hpp"
#include <vector>
#include <algorithm>

class Room {
private:
    std::string                 room_name;
    NicknameStorage             *room_users;
    NicknameStorage             *oper_nicknames;
//    int                         type;
    int                         mode;

public:
//    Room(std::string creator, std::string joiner);
    Room(std::string creator, int selected_mode);
    Room(std::string creator, int selected_mode, std::string set_room_name);
    ~Room();

    std::string get_room_name();
//    int         get_room_type();
    void        set_room_name(std::string new_name);
    int         user_join(std::string joined_user);
    int         user_leave(std::string leaved_user);
    int         set_mode(int selected_mode);
    int         is_oper(std::string nickname);
    int         set_oper(std::string reporter, std::string new_oper);
    int         get_users_capacity();
};


#endif //IRC_ROOM_HPP
