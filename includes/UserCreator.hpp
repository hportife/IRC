#ifndef IRC_USERCREATOR_HPP
#define IRC_USERCREATOR_HPP

#include "User.hpp"

class UserCreator
{
private:
    NicknameStorage     *nickname_storage;
    int                 id;
    std::string         password;
    std::string         correct_password;
    std::string         nickname;
    std::string         realname;
    User                *tmp_user;

public:
    UserCreator(int tmp_id, NicknameStorage *tmp_storage, std::string server_password);
    ~UserCreator();

//    void    set_id(int tmp_id);
    void    set_password(std::string tmp_pass);
    void    set_nickname(std::string tmp_nickname);
    void    set_realname(std::string tmp_realname);

    User    *get_ready_user();

    int     pass_validation(std::string correct_pass);
    int     nickname_validation(std::string tested_nickname);
    int     parameter_validation(std::string correct_pass);
    int     swap_nickname(User *user, std::string new_nickname);
};

#endif //IRC_USERCREATOR_HPP
