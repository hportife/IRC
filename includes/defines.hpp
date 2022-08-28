#ifndef IRC_DEFINES_HPP
#define IRC_DEFINES_HPP
//#include "defines.hpp"

#define FLG_SRV_WORK                2000
#define FLG_SRV_DOWN                2010
#define FLG_SRV_RSTRT               2020

#define ISNOCOMMANT                 2030
#define ISCOMMAND                   2040

#define NICKNAMEISMAYBEGIVEN        1010
#define ERR_NICKNAMEINUSE           1011
#define ERR_NICKNAMEISTOOLONG       1012
#define ERR_NICKNAMEISEMPTY         1013
#define NICKNAMEHASBEENGIVEN        1014
//#define SIMPLE_VALUE                111

#define ROOM_MODE_PRIVATE           301
#define ROOM_MODE_PUBLIC            302
#define USER_IS_OPER                311
#define USER_IS_NOT_OPER            312
#define USER_IN_ROOM                321
#define USER_NOT_IN_ROOM            322
#define JOIN_COMPLETE               323
#define LEAVE_COMPLETE              324

#define ROOM_IN_STORAGE             400
#define ROOM_NOT_IN_STORAGE         401
#define DELETE_HAS_BEEN_COMPLETE    402

#define CORRPASS                    1000
#define INCORRPASS                  1001
#define INCORRNICKNAME              1002
#define NICKNAMEISMAYBEGIVEN        1010
#define ERR_NICKNAMEINUSE           1011
#define ERR_NICKNAMEISTOOLONG       1012
#define ERR_NICKNAMEISEMPTY         1013
#define NICKNAMEHASBEENGIVEN        1014

#define NICKNAME_IS_WRONG           113
#define NICKNAME_IS_GIVEN           114
#define NICKNAME_HAS_VALID          115
#define NEW_USER_CREATE             116
#define WRONGPASSWORD               117

#endif //IRC_DEFINES_HPP
