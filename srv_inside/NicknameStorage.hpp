#ifndef IRC_NICKNAMESTORAGE_HPP
#define IRC_NICKNAMESTORAGE_HPP

#include "../tools/LogIdentifier.hpp"
#include <iostream>
#include <vector>

class NicknameStorage{
private:
    std::vector<std::string>    storage;
    int                         storage_capacity;

public:
    NicknameStorage();
    ~NicknameStorage();

    int         get_storage_capacity();
    void        get_storage();

    void        add_nickname(std::string added_nickname);
    int         delete_nickname(std::string deleted_nickname);
    int         search_a_conflict(std::string searched_nickname);
};

#endif