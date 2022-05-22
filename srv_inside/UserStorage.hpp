#ifndef IRC_USERSTORAGE_HPP
#define IRC_USERSTORAGE_HPP

#include "User.hpp"

class UserStorage
{
private:
    std::vector<user> user_storage;

public:
    UserStorage();
    ~UserStorage();

    void    add_user(user user_for_add);
    user    *search_by_nickname(std::string searched_nickname);
    user    *search_by_id(int searched_id);
};
#endif