#ifndef IRC_USER_HPP
#define IRC_USER_HPP

#define CORRPASS                1000
#define INCORRPASS              1001
#define INCORRNICKNAME          1002
#define NICKNAMEISMAYBEGIVEN    1010
#define ERR_NICKNAMEINUSE       1011
#define ERR_NICKNAMEISTOOLONG   1012
#define ERR_NICKNAMEISEMPTY     1013
#define NICKNAMEHASBEENGIVEN    1014

#include "../tools/LogIdentifier.hpp"
#include "NicknameStorage.hpp"
#include <iostream>

class User {
private:
    std::string         user_nickname;
    std::string         user_realname;
    std::string         client_name;
    int                 user_id;

public:
    User(std::string nickname, int id,
         std::string realname, std::string clientname);
    ~User();

    void set_nickname(std::string new_nickname);

    std::string get_user_realname() const;
    std::string get_user_nickname() const;
    std::string get_client_name() const;
    int         get_user_id() const;
    User        *clone() const;
};

#endif //IRC_USER_HPP
