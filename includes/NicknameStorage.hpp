#ifndef IRC_NICKNAMESTORAGE_HPP
#define IRC_NICKNAMESTORAGE_HPP

#include <vector>
#include <algorithm>
#include <map>
#include "defines.hpp"

class NicknameStorage{
private:
    std::map<std::string, int>  storage;

public:
    NicknameStorage();
    ~NicknameStorage();

    void        print_storage();

    int         check_size_added_nickname(std::string added_nickname);
    void        add_nickname(std::string added_nickname);
    int         delete_nickname(std::string deleted_nickname);
    int         search_a_conflict(std::string searched_nickname);
    std::string getNicknameWithValue(int value);
    int         get_value(std::string checked_nickname);
    int         set_value(std::string nickname, int value);
    int         get_capacity();
};

#endif