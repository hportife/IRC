#ifndef IRC_NICKNAME_STORAGE_HPP
#define IRC_NICKNAME_STORAGE_HPP

#include <iostream>
#include <vector>

class nickname_storage{
private:
    std::vector<std::string>    storage;
    int                         storage_capacity;

public:
    nickname_storage();
    ~nickname_storage();

    void    add_nickname(std::string added_nickname);
    int     delete_nickname(std::string deleted_nickname);
    int     search_a_conflict(std::string searched_nickname);
};

#endif