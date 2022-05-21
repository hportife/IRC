#ifndef IRC_USER_HPP
#define IRC_USER_HPP

#define CORRPASS                1000
#define INCORRPASS              1001
#define NICKNAMEISMAYBEGIVEN    1010
#define ERR_NICKNAMEINUSE       1011
#define ERR_NICKNAMEISTOOLONG   1012
#define NICKNAMEHASBEENGIVEN    1013

#include "NicknameStorage.hpp"
#include "../tools/LogIdentifier.hpp"
#include <iostream>

class user {
private:
    std::string         user_login;
    std::string         user_nickname;
    std::string         user_realname;
    int                 user_id;
public:


    user();
    user(std::string login, std::string nickname, int id, std::string realname);
    ~user();

    void set_nickname(std::string new_nickname);

    std::string get_user_login();
    std::string get_user_realname();
    std::string get_user_nickname();
    int         get_user_id();
};

class user_creator
{
private:
    int                 id;
    std::string         password;
    std::string         correct_password;
    std::string         login;
    std::string         nickname;
    std::string         realname;
    user                tmp_user;
    NicknameStorage     *nickname_storage;

public:
    user_creator(int tmp_id, NicknameStorage *tmp_storage, std::string server_password);
    ~user_creator();

//    void    set_id(int tmp_id);
    void    set_password(std::string tmp_pass);
    void    set_login(std::string tmp_login);
    void    set_nickname(std::string tmp_nickname);
    void    set_realname(std::string tmp_realname);

    user    *get_ready_user();

    int     pass_validation(std::string correct_pass);
    int     nickname_validation(std::string tested_nickname);
    int     parameter_validation(std::string correct_pass);
    int    swap_nickname(user *user, std::string new_nickname);
};

#endif //IRC_USER_HPP
