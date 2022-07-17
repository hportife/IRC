#ifndef IRC_USERSTORAGE_HPP
#define IRC_USERSTORAGE_HPP

#include "User.hpp"
#include "NicknameStorage.hpp"

class UserStorage
{
private:
    std::vector<User>   user_storage;
    NicknameStorage     *ptr_to_nickname_storage;

public:
    UserStorage(NicknameStorage *ptr_to_nickname_storage);
    ~UserStorage();

    void    add_user(User user_for_add);
    User    *search_by_nickname(std::string searched_nickname);
    User    *search_by_id(int searched_id);
    int     get_user_position_in_storage(User *user);
    int     delete_user_from_storage(User *user);
};
#endif