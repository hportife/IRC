#ifndef IRC_NICKNAMESTORAGE_HPP
#define IRC_NICKNAMESTORAGE_HPP

#include <vector>
#include <algorithm>
#include "../tools/LogIdentifier.hpp"
#include "user.hpp"

class NicknameStorage{
private:
    std::vector<std::string>    storage;
    int                         storage_capacity;

public:
    NicknameStorage();
    ~NicknameStorage();

    int         get_storage_capacity();
    void        get_storage();

    int         add_nickname(std::string added_nickname);
    int         delete_nickname(std::string deleted_nickname);
    int         search_a_conflict(std::string searched_nickname);
    void        sort_a_storage();
};

#endif