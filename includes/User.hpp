#ifndef IRC_USER_HPP
#define IRC_USER_HPP

#include "LogIdentifier.hpp"
#include "NicknameStorage.hpp"
#include <iostream>
#include "defines.hpp"

class User {
private:
    std::string                 user_nickname;
    std::string                 user_realname;
    std::string                 client_name;
    int                         user_id;
    std::string                 away_msg;
    std::map<std::string, bool> user_params;

    std::map<std::string, bool> initUserParams();

public:
    User(std::string nickname, int id,
         std::string realname, std::string clientname);//got
    ~User();//got

    void set_nickname(std::string new_nickname);//got

    std::string get_user_realname() const;//got
    std::string get_user_nickname() const;//got
    std::string get_client_name() const;//got
    int         get_user_id() const;//got
    bool        getUserParamValue(std::string param);
    void        setUserParamValue(std::string param, bool value);
    void        setAwayMsg(std::string away_msg);//got
    void        setAwayMsg();//got
    bool        isAwayMsg();//got
    std::string getAwayMsg()const;//got
    User        *clone() const;//got
};

#endif //IRC_USER_HPP
