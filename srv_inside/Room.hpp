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
#include <map>
#include <algorithm>

class Room {
private:
    std::string                 room_name;
    NicknameStorage             *room_users;
    std::vector<std::string>    invite_list;
    std::map<std::string, bool> room_params;
    std::string                 room_password;
    int                         users_limit;

    Room();
    Room(std::string creator);
    Room(std::string creator, int selected_mode);
    std::map<std::string, bool> initRoomParams();//реализованно
public:
    Room(std::string creator, std::string set_room_name);
    ~Room();

    std::string get_room_name() const;//реализовано
    int         get_users_capacity() const;//реализовано
    std::string get_room_password() const;//реализовано
    bool        get_param_value(std::string param_name);//реализовано

    void        set_room_name(std::string const new_name);//реализовано
    void        set_room_password(std::string const password);//реализовано
    void        set_room_parameter(std::string const parameter, bool value);//реализовано
    void        set_oper(std::string const new_oper);//реализовано
    void        unset_oper(std::string const deleted_oper);//реализовано
    void        set_user_limit(int limit);

    void        add_user(std::string const nickname);//реализованно
    void        delete_user(std::string const nickname);//реализованно
    void        add_to_invite_list(std::string const nickname);//реализовано

    bool        is_oper(std::string nickname);//реализовано
    bool        is_in_invite_list(std::string nickname);//реализовано
};


#endif //IRC_ROOM_HPP
