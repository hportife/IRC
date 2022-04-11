#ifndef IRC_USER_HPP
#define IRC_USER_HPP

#include <iostream>

class user {
private:
    std::string user_login;
    std::string user_nickname;
    int         user_id;

public:
    user();
    ~user();

    std::string get_user_login();
    std::string get_user_nickname();
    int         get_user_id();
};


#endif //IRC_USER_HPP
