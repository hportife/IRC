#ifndef IRC_USER_HPP
#define IRC_USER_HPP

#define CORRPASS                1000
#define INCORRPASS              1001
#define NICKNAMEISMAYBEGIVEN    1010
#define ERR_NICKNAMEINUSE       1011

#include <iostream>

class user {
private:
    std::string user_login;
    std::string user_nickname;
    int         user_id;

public:
    user();
    user(std::string login, std::string nickname, int id);
    ~user();

    std::string get_user_login();
    std::string get_user_nickname();
    int         get_user_id();
};

class user_creator
{
private:
    int         id;
    std::string password;
    std::string login;
    std::string nickname;
    std::string realname;
    user        tmp_user;

public:
    user_creator(int tmp_id);
    ~user_creator();

//    void    set_id(int tmp_id);
    void    set_password(std::string tmp_pass);
    void    set_login(std::string tmp_login);
    void    set_nickname(std::string tmp_nickname);
    void    set_realname(std::string tmp_realname);

    int     pass_validation(std::string correct_pass);
    int     parameter_validation(std::string correct_pass);
};

#endif //IRC_USER_HPP
