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
//Нужно инкапсулировать логику вычислени оператора.
//Исполнитель должен будет перед исполнением проверять
//права пользователя на исполнение оманд
class Room {
private:
    std::string                 room_name;
    NicknameStorage             *room_users;
    std::vector<std::string>    invite_list;
    std::map<std::string, bool> room_params;
    std::string                 room_password;

    Room();
    Room(std::string creator);
    Room(std::string creator, int selected_mode);
    std::map<std::string, bool> initRoomParams();//OK
public:
    Room(std::string creator, int selected_mode, std::string set_room_name);
    ~Room();

    std::string get_room_name() const;//реализовано
    int         get_users_capacity() const;//реализовано
    std::string get_room_password() const;//реализовано

    void        set_room_name(std::string const new_name);//реализовано
    void        set_room_password(std::string const password);//реализовано
    void        set_room_parameter(std::string const parameter);//реализовано
    void        unset_room_parameter(std::string const parameter);//реализовано
    void        set_oper(std::string const new_oper);//реализовано
    void        unset_oper(std::string const deleted_oper);//реализовано

    int         is_oper(std::string nickname);

    int         user_join(std::string const joined_user);
    int         user_leave(std::string const leaved_user);
    int         delete_user(std::string const reporter,
                            std::string const deleted_user);
};


#endif //IRC_ROOM_HPP
